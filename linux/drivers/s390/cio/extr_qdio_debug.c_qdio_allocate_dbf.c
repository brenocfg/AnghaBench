#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qdio_irq {int /*<<< orphan*/  debug_area; } ;
struct qdio_initialize {unsigned long q_format; unsigned long qib_param_field_format; TYPE_1__* cdev; int /*<<< orphan*/  output_sbal_addr_array; int /*<<< orphan*/  input_sbal_addr_array; int /*<<< orphan*/  int_parm; int /*<<< orphan*/  output_handler; int /*<<< orphan*/  input_handler; int /*<<< orphan*/  no_output_qs; int /*<<< orphan*/  no_input_qs; int /*<<< orphan*/  output_slib_elements; int /*<<< orphan*/  input_slib_elements; int /*<<< orphan*/  qib_param_field; int /*<<< orphan*/ * adapter_name; } ;
struct qdio_dbf_entry {int /*<<< orphan*/  dbf_list; int /*<<< orphan*/  dbf_info; int /*<<< orphan*/  dbf_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct qdio_irq*,char*) ; 
 int /*<<< orphan*/  DBF_ERR ; 
 int /*<<< orphan*/  DBF_EVENT (char*,unsigned long,...) ; 
 int /*<<< orphan*/  DBF_HEX (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DBF_WARN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QDIO_DBF_NAME_LEN ; 
 int /*<<< orphan*/  debug_hex_ascii_view ; 
 int /*<<< orphan*/  debug_register (char*,int,int,int) ; 
 scalar_t__ debug_register_view (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_set_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_unregister (int /*<<< orphan*/ ) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 struct qdio_dbf_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdio_dbf_list ; 
 int /*<<< orphan*/  qdio_dbf_list_mutex ; 
 int /*<<< orphan*/  qdio_get_dbf_entry (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

int qdio_allocate_dbf(struct qdio_initialize *init_data,
		       struct qdio_irq *irq_ptr)
{
	char text[QDIO_DBF_NAME_LEN];
	struct qdio_dbf_entry *new_entry;

	DBF_EVENT("qfmt:%1d", init_data->q_format);
	DBF_HEX(init_data->adapter_name, 8);
	DBF_EVENT("qpff%4x", init_data->qib_param_field_format);
	DBF_HEX(&init_data->qib_param_field, sizeof(void *));
	DBF_HEX(&init_data->input_slib_elements, sizeof(void *));
	DBF_HEX(&init_data->output_slib_elements, sizeof(void *));
	DBF_EVENT("niq:%1d noq:%1d", init_data->no_input_qs,
		  init_data->no_output_qs);
	DBF_HEX(&init_data->input_handler, sizeof(void *));
	DBF_HEX(&init_data->output_handler, sizeof(void *));
	DBF_HEX(&init_data->int_parm, sizeof(long));
	DBF_HEX(&init_data->input_sbal_addr_array, sizeof(void *));
	DBF_HEX(&init_data->output_sbal_addr_array, sizeof(void *));
	DBF_EVENT("irq:%8lx", (unsigned long)irq_ptr);

	/* allocate trace view for the interface */
	snprintf(text, QDIO_DBF_NAME_LEN, "qdio_%s",
					dev_name(&init_data->cdev->dev));
	irq_ptr->debug_area = qdio_get_dbf_entry(text);
	if (irq_ptr->debug_area)
		DBF_DEV_EVENT(DBF_ERR, irq_ptr, "dbf reused");
	else {
		irq_ptr->debug_area = debug_register(text, 2, 1, 16);
		if (!irq_ptr->debug_area)
			return -ENOMEM;
		if (debug_register_view(irq_ptr->debug_area,
						&debug_hex_ascii_view)) {
			debug_unregister(irq_ptr->debug_area);
			return -ENOMEM;
		}
		debug_set_level(irq_ptr->debug_area, DBF_WARN);
		DBF_DEV_EVENT(DBF_ERR, irq_ptr, "dbf created");
		new_entry = kzalloc(sizeof(struct qdio_dbf_entry), GFP_KERNEL);
		if (!new_entry) {
			debug_unregister(irq_ptr->debug_area);
			return -ENOMEM;
		}
		strlcpy(new_entry->dbf_name, text, QDIO_DBF_NAME_LEN);
		new_entry->dbf_info = irq_ptr->debug_area;
		mutex_lock(&qdio_dbf_list_mutex);
		list_add(&new_entry->dbf_list, &qdio_dbf_list);
		mutex_unlock(&qdio_dbf_list_mutex);
	}
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {int type; } ;
struct TYPE_16__ {int /*<<< orphan*/  resource_order; int /*<<< orphan*/  system_level; } ;
struct TYPE_14__ {int /*<<< orphan*/  length; int /*<<< orphan*/  address; int /*<<< orphan*/  proc_id; } ;
struct TYPE_25__ {int /*<<< orphan*/  node; int /*<<< orphan*/  class; } ;
struct TYPE_23__ {int /*<<< orphan*/  value; } ;
struct TYPE_21__ {int /*<<< orphan*/  length; scalar_t__ pointer; } ;
struct TYPE_20__ {int /*<<< orphan*/  length; scalar_t__ pointer; } ;
union acpi_operand_object {TYPE_13__ common; TYPE_12__ power_resource; TYPE_10__ processor; TYPE_8__ reference; TYPE_6__ integer; TYPE_4__ buffer; TYPE_3__ string; } ;
struct TYPE_15__ {int /*<<< orphan*/  resource_order; int /*<<< orphan*/  system_level; } ;
struct TYPE_26__ {int /*<<< orphan*/  pblk_length; int /*<<< orphan*/  pblk_address; int /*<<< orphan*/  proc_id; } ;
struct TYPE_24__ {int /*<<< orphan*/  actual_type; int /*<<< orphan*/  handle; } ;
struct TYPE_22__ {int /*<<< orphan*/  value; } ;
struct TYPE_19__ {int /*<<< orphan*/  length; int /*<<< orphan*/ * pointer; } ;
struct TYPE_18__ {char* pointer; int /*<<< orphan*/  length; } ;
union acpi_object {int type; TYPE_11__ power_resource; TYPE_9__ processor; TYPE_7__ reference; TYPE_5__ integer; TYPE_2__ buffer; TYPE_1__ string; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
#define  ACPI_REFCLASS_NAME 134 
 scalar_t__ ACPI_ROUND_UP_TO_NATIVE_WORD (int /*<<< orphan*/ ) ; 
#define  ACPI_TYPE_BUFFER 133 
#define  ACPI_TYPE_INTEGER 132 
#define  ACPI_TYPE_LOCAL_REFERENCE 131 
#define  ACPI_TYPE_POWER 130 
#define  ACPI_TYPE_PROCESSOR 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_SUPPORT ; 
 int /*<<< orphan*/  AE_TYPE ; 
 int /*<<< orphan*/  acpi_ns_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union acpi_object*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_copy_isimple_to_esimple ; 

__attribute__((used)) static acpi_status
acpi_ut_copy_isimple_to_esimple(union acpi_operand_object *internal_object,
				union acpi_object *external_object,
				u8 *data_space, acpi_size *buffer_space_used)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ut_copy_isimple_to_esimple);

	*buffer_space_used = 0;

	/*
	 * Check for NULL object case (could be an uninitialized
	 * package element)
	 */
	if (!internal_object) {
		return_ACPI_STATUS(AE_OK);
	}

	/* Always clear the external object */

	memset(external_object, 0, sizeof(union acpi_object));

	/*
	 * In general, the external object will be the same type as
	 * the internal object
	 */
	external_object->type = internal_object->common.type;

	/* However, only a limited number of external types are supported */

	switch (internal_object->common.type) {
	case ACPI_TYPE_STRING:

		external_object->string.pointer = (char *)data_space;
		external_object->string.length = internal_object->string.length;
		*buffer_space_used = ACPI_ROUND_UP_TO_NATIVE_WORD((acpi_size)
								  internal_object->
								  string.
								  length + 1);

		memcpy((void *)data_space,
		       (void *)internal_object->string.pointer,
		       (acpi_size)internal_object->string.length + 1);
		break;

	case ACPI_TYPE_BUFFER:

		external_object->buffer.pointer = data_space;
		external_object->buffer.length = internal_object->buffer.length;
		*buffer_space_used =
		    ACPI_ROUND_UP_TO_NATIVE_WORD(internal_object->string.
						 length);

		memcpy((void *)data_space,
		       (void *)internal_object->buffer.pointer,
		       internal_object->buffer.length);
		break;

	case ACPI_TYPE_INTEGER:

		external_object->integer.value = internal_object->integer.value;
		break;

	case ACPI_TYPE_LOCAL_REFERENCE:

		/* This is an object reference. */

		switch (internal_object->reference.class) {
		case ACPI_REFCLASS_NAME:
			/*
			 * For namepath, return the object handle ("reference")
			 * We are referring to the namespace node
			 */
			external_object->reference.handle =
			    internal_object->reference.node;
			external_object->reference.actual_type =
			    acpi_ns_get_type(internal_object->reference.node);
			break;

		default:

			/* All other reference types are unsupported */

			return_ACPI_STATUS(AE_TYPE);
		}
		break;

	case ACPI_TYPE_PROCESSOR:

		external_object->processor.proc_id =
		    internal_object->processor.proc_id;
		external_object->processor.pblk_address =
		    internal_object->processor.address;
		external_object->processor.pblk_length =
		    internal_object->processor.length;
		break;

	case ACPI_TYPE_POWER:

		external_object->power_resource.system_level =
		    internal_object->power_resource.system_level;

		external_object->power_resource.resource_order =
		    internal_object->power_resource.resource_order;
		break;

	default:
		/*
		 * There is no corresponding external object type
		 */
		ACPI_ERROR((AE_INFO,
			    "Unsupported object type, cannot convert to external object: %s",
			    acpi_ut_get_type_name(internal_object->common.
						  type)));

		return_ACPI_STATUS(AE_SUPPORT);
	}

	return_ACPI_STATUS(status);
}
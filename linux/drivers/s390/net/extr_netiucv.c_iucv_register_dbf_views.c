#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IUCV_DBF_DATA_LEN ; 
 int /*<<< orphan*/  IUCV_DBF_DATA_LEVEL ; 
 int /*<<< orphan*/  IUCV_DBF_DATA_NAME ; 
 int /*<<< orphan*/  IUCV_DBF_DATA_NR_AREAS ; 
 int /*<<< orphan*/  IUCV_DBF_DATA_PAGES ; 
 int /*<<< orphan*/  IUCV_DBF_SETUP_LEN ; 
 int /*<<< orphan*/  IUCV_DBF_SETUP_LEVEL ; 
 int /*<<< orphan*/  IUCV_DBF_SETUP_NAME ; 
 int /*<<< orphan*/  IUCV_DBF_SETUP_NR_AREAS ; 
 int /*<<< orphan*/  IUCV_DBF_SETUP_PAGES ; 
 int /*<<< orphan*/  IUCV_DBF_TRACE_LEN ; 
 int /*<<< orphan*/  IUCV_DBF_TRACE_LEVEL ; 
 int /*<<< orphan*/  IUCV_DBF_TRACE_NAME ; 
 int /*<<< orphan*/  IUCV_DBF_TRACE_NR_AREAS ; 
 int /*<<< orphan*/  IUCV_DBF_TRACE_PAGES ; 
 int /*<<< orphan*/  debug_hex_ascii_view ; 
 int /*<<< orphan*/ * debug_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_register_view (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_set_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iucv_dbf_data ; 
 int /*<<< orphan*/ * iucv_dbf_setup ; 
 int /*<<< orphan*/ * iucv_dbf_trace ; 
 int /*<<< orphan*/  iucv_unregister_dbf_views () ; 

__attribute__((used)) static int iucv_register_dbf_views(void)
{
	iucv_dbf_setup = debug_register(IUCV_DBF_SETUP_NAME,
					IUCV_DBF_SETUP_PAGES,
					IUCV_DBF_SETUP_NR_AREAS,
					IUCV_DBF_SETUP_LEN);
	iucv_dbf_data = debug_register(IUCV_DBF_DATA_NAME,
				       IUCV_DBF_DATA_PAGES,
				       IUCV_DBF_DATA_NR_AREAS,
				       IUCV_DBF_DATA_LEN);
	iucv_dbf_trace = debug_register(IUCV_DBF_TRACE_NAME,
					IUCV_DBF_TRACE_PAGES,
					IUCV_DBF_TRACE_NR_AREAS,
					IUCV_DBF_TRACE_LEN);

	if ((iucv_dbf_setup == NULL) || (iucv_dbf_data == NULL) ||
	    (iucv_dbf_trace == NULL)) {
		iucv_unregister_dbf_views();
		return -ENOMEM;
	}
	debug_register_view(iucv_dbf_setup, &debug_hex_ascii_view);
	debug_set_level(iucv_dbf_setup, IUCV_DBF_SETUP_LEVEL);

	debug_register_view(iucv_dbf_data, &debug_hex_ascii_view);
	debug_set_level(iucv_dbf_data, IUCV_DBF_DATA_LEVEL);

	debug_register_view(iucv_dbf_trace, &debug_hex_ascii_view);
	debug_set_level(iucv_dbf_trace, IUCV_DBF_TRACE_LEVEL);

	return 0;
}
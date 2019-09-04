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
typedef  enum mei_cl_connect_status { ____Placeholder_mei_cl_connect_status } mei_cl_connect_status ;

/* Variables and functions */
#define  MEI_CL_CONN_ALREADY_STARTED 133 
#define  MEI_CL_CONN_MESSAGE_SMALL 132 
#define  MEI_CL_CONN_NOT_ALLOWED 131 
#define  MEI_CL_CONN_NOT_FOUND 130 
#define  MEI_CL_CONN_OUT_OF_RESOURCES 129 
#define  MEI_CL_CONN_SUCCESS 128 

__attribute__((used)) static const char *mei_cl_conn_status_str(enum mei_cl_connect_status status)
{
#define MEI_CL_CS(status) case MEI_CL_CONN_##status: return #status
	switch (status) {
	MEI_CL_CS(SUCCESS);
	MEI_CL_CS(NOT_FOUND);
	MEI_CL_CS(ALREADY_STARTED);
	MEI_CL_CS(OUT_OF_RESOURCES);
	MEI_CL_CS(MESSAGE_SMALL);
	MEI_CL_CS(NOT_ALLOWED);
	default: return "unknown";
	}
#undef MEI_CL_CCS
}
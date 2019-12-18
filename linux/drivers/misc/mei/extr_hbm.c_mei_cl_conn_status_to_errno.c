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
 int EBUSY ; 
 int EINVAL ; 
 int ENOTTY ; 
#define  MEI_CL_CONN_ALREADY_STARTED 133 
#define  MEI_CL_CONN_MESSAGE_SMALL 132 
#define  MEI_CL_CONN_NOT_ALLOWED 131 
#define  MEI_CL_CONN_NOT_FOUND 130 
#define  MEI_CL_CONN_OUT_OF_RESOURCES 129 
#define  MEI_CL_CONN_SUCCESS 128 

__attribute__((used)) static int mei_cl_conn_status_to_errno(enum mei_cl_connect_status status)
{
	switch (status) {
	case MEI_CL_CONN_SUCCESS:          return 0;
	case MEI_CL_CONN_NOT_FOUND:        return -ENOTTY;
	case MEI_CL_CONN_ALREADY_STARTED:  return -EBUSY;
	case MEI_CL_CONN_OUT_OF_RESOURCES: return -EBUSY;
	case MEI_CL_CONN_MESSAGE_SMALL:    return -EINVAL;
	case MEI_CL_CONN_NOT_ALLOWED:      return -EBUSY;
	default:                           return -EINVAL;
	}
}
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
struct mei_device {int dummy; } ;
struct mei_cl {int dummy; } ;
struct hbm_client_connect_response {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_DISCONNECT_RES_CMD ; 
 int mei_hbm_cl_write (struct mei_device*,struct mei_cl*,int /*<<< orphan*/ ,struct hbm_client_connect_response*,int) ; 

int mei_hbm_cl_disconnect_rsp(struct mei_device *dev, struct mei_cl *cl)
{
	struct hbm_client_connect_response resp;

	return mei_hbm_cl_write(dev, cl, CLIENT_DISCONNECT_RES_CMD,
				&resp, sizeof(resp));
}
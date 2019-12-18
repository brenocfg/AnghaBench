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
typedef  int /*<<< orphan*/  u8 ;
struct cmd_obj {int dummy; } ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2C_SUCCESS ; 
 int /*<<< orphan*/  r8712_free_cmd_obj (struct cmd_obj*) ; 

__attribute__((used)) static u8 sys_suspend_hdl(struct _adapter *padapter, u8 *pbuf)
{
	struct cmd_obj *pcmd  = (struct cmd_obj *)pbuf;

	r8712_free_cmd_obj(pcmd);
	return H2C_SUCCESS;
}
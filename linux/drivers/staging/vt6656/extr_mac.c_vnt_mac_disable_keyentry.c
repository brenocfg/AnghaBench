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
struct vnt_private {int dummy; } ;
typedef  int /*<<< orphan*/  entry_idx ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_TYPE_CLRKEYENTRY ; 
 int /*<<< orphan*/  vnt_control_out (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void vnt_mac_disable_keyentry(struct vnt_private *priv, u8 entry_idx)
{
	vnt_control_out(priv, MESSAGE_TYPE_CLRKEYENTRY, 0, 0,
			sizeof(entry_idx), &entry_idx);
}
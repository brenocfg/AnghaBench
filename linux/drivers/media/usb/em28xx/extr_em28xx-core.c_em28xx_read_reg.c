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
typedef  int /*<<< orphan*/  u16 ;
struct em28xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_REQ_GET_STATUS ; 
 int em28xx_read_reg_req (struct em28xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int em28xx_read_reg(struct em28xx *dev, u16 reg)
{
	return em28xx_read_reg_req(dev, USB_REQ_GET_STATUS, reg);
}
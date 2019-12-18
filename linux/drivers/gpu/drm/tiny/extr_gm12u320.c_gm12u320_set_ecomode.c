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
struct gm12u320_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MISC_REQ_GET_SET_ECO_A ; 
 int /*<<< orphan*/  MISC_REQ_GET_SET_ECO_B ; 
 scalar_t__ eco_mode ; 
 int gm12u320_misc_request (struct gm12u320_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int gm12u320_set_ecomode(struct gm12u320_device *gm12u320)
{
	return gm12u320_misc_request(gm12u320, MISC_REQ_GET_SET_ECO_A,
				     MISC_REQ_GET_SET_ECO_B, 0x01 /* set */,
				     eco_mode ? 0x01 : 0x00, 0x00, 0x01);
}
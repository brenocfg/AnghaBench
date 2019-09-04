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
struct bttv {int hue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_HUE ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bt848_hue(struct bttv *btv, int hue)
{
	int value;

	btv->hue = hue;

	/* -128 to 127 */
	value = (hue >> 8) - 128;
	btwrite(value & 0xff, BT848_HUE);
}
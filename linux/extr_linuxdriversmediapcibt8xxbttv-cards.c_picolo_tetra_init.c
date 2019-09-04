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
struct bttv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_GPIO_DATA ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void picolo_tetra_init(struct bttv *btv)
{
	/*This is the video input redirection fonctionality : I DID NOT USED IT. */
	btwrite (0x08<<16,BT848_GPIO_DATA);/*GPIO[19] [==> 4053 B+C] set to 1 */
	btwrite (0x04<<16,BT848_GPIO_DATA);/*GPIO[18] [==> 4053 A]  set to 1*/
}
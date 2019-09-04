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
struct cardinfo {int dummy; } ;
struct blk_plug_cb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_check_plugged (int /*<<< orphan*/ ,struct cardinfo*,int) ; 
 int /*<<< orphan*/  mm_unplug ; 

__attribute__((used)) static int mm_check_plugged(struct cardinfo *card)
{
	return !!blk_check_plugged(mm_unplug, card, sizeof(struct blk_plug_cb));
}
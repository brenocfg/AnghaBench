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
typedef  int /*<<< orphan*/  u32 ;
struct osd_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSD_BASEPY ; 
 int /*<<< orphan*/  osd_write (struct osd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void osd_set_top_margin(struct osd_state *sd, u32 val)
{
	osd_write(sd, val, OSD_BASEPY);
}
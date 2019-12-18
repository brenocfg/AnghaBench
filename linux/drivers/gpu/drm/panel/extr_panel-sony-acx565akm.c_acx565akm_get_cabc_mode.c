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
struct acx565akm_panel {unsigned int cabc_mode; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int acx565akm_get_cabc_mode(struct acx565akm_panel *lcd)
{
	return lcd->cabc_mode;
}
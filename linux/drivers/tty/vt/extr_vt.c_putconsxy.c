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
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gotoxy (struct vc_data*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  hide_cursor (struct vc_data*) ; 
 int /*<<< orphan*/  set_cursor (struct vc_data*) ; 

void putconsxy(struct vc_data *vc, unsigned char *p)
{
	hide_cursor(vc);
	gotoxy(vc, p[0], p[1]);
	set_cursor(vc);
}
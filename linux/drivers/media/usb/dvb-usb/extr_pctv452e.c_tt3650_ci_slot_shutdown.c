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
struct dvb_ca_en50221 {int dummy; } ;

/* Variables and functions */
 int tt3650_ci_set_video_port (struct dvb_ca_en50221*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tt3650_ci_slot_shutdown(struct dvb_ca_en50221 *ca, int slot)
{
	return tt3650_ci_set_video_port(ca, slot, /* enable */ 0);
}
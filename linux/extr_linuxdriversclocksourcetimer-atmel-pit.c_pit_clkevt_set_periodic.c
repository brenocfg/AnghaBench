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
struct pit_data {int cnt; int cycle; int /*<<< orphan*/  base; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PIT_MR ; 
 int AT91_PIT_PITEN ; 
 int AT91_PIT_PITIEN ; 
 int /*<<< orphan*/  AT91_PIT_PIVR ; 
 int PIT_PICNT (int /*<<< orphan*/ ) ; 
 struct pit_data* clkevt_to_pit_data (struct clock_event_device*) ; 
 int /*<<< orphan*/  pit_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pit_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pit_clkevt_set_periodic(struct clock_event_device *dev)
{
	struct pit_data *data = clkevt_to_pit_data(dev);

	/* update clocksource counter */
	data->cnt += data->cycle * PIT_PICNT(pit_read(data->base, AT91_PIT_PIVR));
	pit_write(data->base, AT91_PIT_MR,
		  (data->cycle - 1) | AT91_PIT_PITEN | AT91_PIT_PITIEN);
	return 0;
}
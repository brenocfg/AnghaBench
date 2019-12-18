#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct initio_host {TYPE_1__* active; } ;
struct TYPE_2__ {int next_state; } ;

/* Variables and functions */
 int initio_bad_seq (struct initio_host*) ; 
 int initio_bus_device_reset (struct initio_host*) ; 
 int initio_state_1 (struct initio_host*) ; 
 int initio_state_2 (struct initio_host*) ; 
 int initio_state_3 (struct initio_host*) ; 
 int initio_state_4 (struct initio_host*) ; 
 int initio_state_5 (struct initio_host*) ; 
 int initio_state_6 (struct initio_host*) ; 
 int initio_state_7 (struct initio_host*) ; 

__attribute__((used)) static int initio_next_state(struct initio_host * host)
{
	int next;

	next = host->active->next_state;
	for (;;) {
		switch (next) {
		case 1:
			next = initio_state_1(host);
			break;
		case 2:
			next = initio_state_2(host);
			break;
		case 3:
			next = initio_state_3(host);
			break;
		case 4:
			next = initio_state_4(host);
			break;
		case 5:
			next = initio_state_5(host);
			break;
		case 6:
			next = initio_state_6(host);
			break;
		case 7:
			next = initio_state_7(host);
			break;
		case 8:
			return initio_bus_device_reset(host);
		default:
			return initio_bad_seq(host);
		}
		if (next <= 0)
			return next;
	}
}
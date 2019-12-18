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
struct gsm_mux {int /*<<< orphan*/  io_error; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSM_SEARCH ; 

__attribute__((used)) static void gsm_error(struct gsm_mux *gsm,
				unsigned char data, unsigned char flag)
{
	gsm->state = GSM_SEARCH;
	gsm->io_error++;
}
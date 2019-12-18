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
struct mic_data {scalar_t__ M; scalar_t__ nBytesInM; int /*<<< orphan*/  K1; int /*<<< orphan*/  R; int /*<<< orphan*/  K0; int /*<<< orphan*/  L; } ;

/* Variables and functions */

__attribute__((used)) static void secmicclear(struct mic_data *pmicdata)
{
/*  Reset the state to the empty message. */
	pmicdata->L = pmicdata->K0;
	pmicdata->R = pmicdata->K1;
	pmicdata->nBytesInM = 0;
	pmicdata->M = 0;
}
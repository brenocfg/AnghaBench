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
struct ni_gpct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ni_tio_acknowledge_and_confirm (struct ni_gpct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ni_tio_acknowledge(struct ni_gpct *counter)
{
	ni_tio_acknowledge_and_confirm(counter, NULL, NULL, NULL);
}
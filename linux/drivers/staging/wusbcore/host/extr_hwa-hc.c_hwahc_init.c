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
struct hwahc {int /*<<< orphan*/  wa; } ;

/* Variables and functions */
 int /*<<< orphan*/  wa_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hwahc_init(struct hwahc *hwahc)
{
	wa_init(&hwahc->wa);
}
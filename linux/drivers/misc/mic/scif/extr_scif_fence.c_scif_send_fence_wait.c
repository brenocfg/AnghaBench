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
typedef  int /*<<< orphan*/  scif_epd_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_WAIT ; 
 int _scif_send_fence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scif_send_fence_wait(scif_epd_t epd, int mark)
{
	return _scif_send_fence(epd, SCIF_WAIT, mark, NULL);
}
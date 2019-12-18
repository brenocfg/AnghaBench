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
struct wil_rx_status_compressed {int /*<<< orphan*/  d0; } ;

/* Variables and functions */
 int WIL_GET_BITS (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline int wil_rx_status_get_error(void *msg)
{
	return WIL_GET_BITS(((struct wil_rx_status_compressed *)msg)->d0,
			    29, 29);
}
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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  tmp ;
struct wl3501_card {scalar_t__ esbq_req_head; scalar_t__ esbq_req_end; scalar_t__ esbq_req_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  wl3501_set_to_wla (struct wl3501_card*,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void wl3501_esbq_req(struct wl3501_card *this, u16 *ptr)
{
	u16 tmp = 0;

	wl3501_set_to_wla(this, this->esbq_req_head, ptr, 2);
	wl3501_set_to_wla(this, this->esbq_req_head + 2, &tmp, sizeof(tmp));
	this->esbq_req_head += 4;
	if (this->esbq_req_head >= this->esbq_req_end)
		this->esbq_req_head = this->esbq_req_start;
}
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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct wl3501_get_req {int /*<<< orphan*/  mib_attrib; int /*<<< orphan*/  sig_id; } ;
struct TYPE_2__ {int mib_status; } ;
struct wl3501_card {int /*<<< orphan*/  lock; TYPE_1__ sig_get_confirm; } ;
typedef  int /*<<< orphan*/  sig ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  WL3501_SIG_GET_REQ ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wl3501_esbq_req (struct wl3501_card*,scalar_t__*) ; 
 scalar_t__ wl3501_esbq_req_test (struct wl3501_card*) ; 
 scalar_t__ wl3501_get_tx_buffer (struct wl3501_card*,int) ; 
 int /*<<< orphan*/  wl3501_set_to_wla (struct wl3501_card*,scalar_t__,struct wl3501_get_req*,int) ; 

__attribute__((used)) static int wl3501_request_mib(struct wl3501_card *this, u8 index, void *bf)
{
	struct wl3501_get_req sig = {
		.sig_id	    = WL3501_SIG_GET_REQ,
		.mib_attrib = index,
	};
	unsigned long flags;
	int rc = -EIO;

	spin_lock_irqsave(&this->lock, flags);
	if (wl3501_esbq_req_test(this)) {
		u16 ptr = wl3501_get_tx_buffer(this, sizeof(sig));
		if (ptr) {
			wl3501_set_to_wla(this, ptr, &sig, sizeof(sig));
			wl3501_esbq_req(this, &ptr);
			this->sig_get_confirm.mib_status = 255;
			rc = 0;
		}
	}
	spin_unlock_irqrestore(&this->lock, flags);

	return rc;
}
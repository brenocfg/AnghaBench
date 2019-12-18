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
struct wiimote_data {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  WIIPROTO_REQ_NULL ; 
 int /*<<< orphan*/  handler_keys (struct wiimote_data*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wiiproto_req_drm (struct wiimote_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handler_status_K(struct wiimote_data *wdata,
			     const __u8 *payload)
{
	handler_keys(wdata, payload);

	/* on status reports the drm is reset so we need to resend the drm */
	wiiproto_req_drm(wdata, WIIPROTO_REQ_NULL);
}
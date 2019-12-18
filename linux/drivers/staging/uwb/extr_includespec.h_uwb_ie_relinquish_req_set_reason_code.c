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
typedef  int u16 ;
struct uwb_relinquish_request_ie {int /*<<< orphan*/  relinquish_req_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void uwb_ie_relinquish_req_set_reason_code(struct uwb_relinquish_request_ie *ie,
							 int reason_code)
{
	u16 ctrl = le16_to_cpu(ie->relinquish_req_control);
	ctrl = (ctrl & ~(0xf << 0)) | (reason_code << 0);
	ie->relinquish_req_control = cpu_to_le16(ctrl);
}
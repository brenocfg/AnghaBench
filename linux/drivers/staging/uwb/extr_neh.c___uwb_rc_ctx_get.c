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
struct uwb_rc_neh {int context; } ;
struct uwb_rc {int /*<<< orphan*/  ctx_bm; int /*<<< orphan*/  ctx_roll; } ;

/* Variables and functions */
 int ENFILE ; 
 int UWB_RC_CTX_MAX ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int __uwb_rc_ctx_get(struct uwb_rc *rc, struct uwb_rc_neh *neh)
{
	int result;
	result = find_next_zero_bit(rc->ctx_bm, UWB_RC_CTX_MAX,
				    rc->ctx_roll++);
	if (result < UWB_RC_CTX_MAX)
		goto found;
	result = find_first_zero_bit(rc->ctx_bm, UWB_RC_CTX_MAX);
	if (result < UWB_RC_CTX_MAX)
		goto found;
	return -ENFILE;
found:
	set_bit(result, rc->ctx_bm);
	neh->context = result;
	return 0;
}
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
struct cec_fh {scalar_t__ mode_initiator; } ;
struct cec_adapter {struct cec_fh const* cec_initiator; struct cec_fh const* cec_follower; } ;

/* Variables and functions */
 scalar_t__ CEC_MODE_NO_INITIATOR ; 

__attribute__((used)) static bool cec_is_busy(const struct cec_adapter *adap,
			const struct cec_fh *fh)
{
	bool valid_initiator = adap->cec_initiator && adap->cec_initiator == fh;
	bool valid_follower = adap->cec_follower && adap->cec_follower == fh;

	/*
	 * Exclusive initiators and followers can always access the CEC adapter
	 */
	if (valid_initiator || valid_follower)
		return false;
	/*
	 * All others can only access the CEC adapter if there is no
	 * exclusive initiator and they are in INITIATOR mode.
	 */
	return adap->cec_initiator ||
	       fh->mode_initiator == CEC_MODE_NO_INITIATOR;
}
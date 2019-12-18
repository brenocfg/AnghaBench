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
struct ath_softc {int dummy; } ;
typedef  enum ath_chanctx_event { ____Placeholder_ath_chanctx_event } ath_chanctx_event ;

/* Variables and functions */

__attribute__((used)) static inline void ath_chanctx_beacon_recv_ev(struct ath_softc *sc,
					      enum ath_chanctx_event ev)
{
}
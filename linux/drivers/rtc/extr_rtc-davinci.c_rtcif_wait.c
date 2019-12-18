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
struct davinci_rtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRTCIF_CTLR ; 
 int PRTCIF_CTLR_BUSY ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int rtcif_read (struct davinci_rtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rtcif_wait(struct davinci_rtc *davinci_rtc)
{
	while (rtcif_read(davinci_rtc, PRTCIF_CTLR) & PRTCIF_CTLR_BUSY)
		cpu_relax();
}
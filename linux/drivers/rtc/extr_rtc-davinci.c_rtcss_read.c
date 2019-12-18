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
typedef  int u8 ;
struct davinci_rtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRTCIF_CTLR ; 
 int PRTCIF_CTLR_BENL_LSB ; 
 int PRTCIF_CTLR_DIR ; 
 int /*<<< orphan*/  PRTCIF_LDATA ; 
 int rtcif_read (struct davinci_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtcif_wait (struct davinci_rtc*) ; 
 int /*<<< orphan*/  rtcif_write (struct davinci_rtc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 rtcss_read(struct davinci_rtc *davinci_rtc, u8 addr)
{
	rtcif_wait(davinci_rtc);

	rtcif_write(davinci_rtc, PRTCIF_CTLR_DIR | PRTCIF_CTLR_BENL_LSB | addr,
		    PRTCIF_CTLR);

	rtcif_wait(davinci_rtc);

	return rtcif_read(davinci_rtc, PRTCIF_LDATA);
}
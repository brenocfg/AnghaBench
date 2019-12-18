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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ OPAL_BUSY ; 
 int OPAL_BUSY_DELAY_MS ; 
 scalar_t__ OPAL_BUSY_EVENT ; 
 scalar_t__ OPAL_HARDWARE ; 
 scalar_t__ OPAL_INTERNAL_ERROR ; 
 scalar_t__ OPAL_SUCCESS ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  opal_poll_events (int /*<<< orphan*/ *) ; 
 scalar_t__ opal_rtc_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opal_to_tm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtc_time*) ; 

__attribute__((used)) static int opal_get_rtc_time(struct device *dev, struct rtc_time *tm)
{
	s64 rc = OPAL_BUSY;
	int retries = 10;
	u32 y_m_d;
	u64 h_m_s_ms;
	__be32 __y_m_d;
	__be64 __h_m_s_ms;

	while (rc == OPAL_BUSY || rc == OPAL_BUSY_EVENT) {
		rc = opal_rtc_read(&__y_m_d, &__h_m_s_ms);
		if (rc == OPAL_BUSY_EVENT) {
			msleep(OPAL_BUSY_DELAY_MS);
			opal_poll_events(NULL);
		} else if (rc == OPAL_BUSY) {
			msleep(OPAL_BUSY_DELAY_MS);
		} else if (rc == OPAL_HARDWARE || rc == OPAL_INTERNAL_ERROR) {
			if (retries--) {
				msleep(10); /* Wait 10ms before retry */
				rc = OPAL_BUSY; /* go around again */
			}
		}
	}

	if (rc != OPAL_SUCCESS)
		return -EIO;

	y_m_d = be32_to_cpu(__y_m_d);
	h_m_s_ms = be64_to_cpu(__h_m_s_ms);
	opal_to_tm(y_m_d, h_m_s_ms, tm);

	return 0;
}
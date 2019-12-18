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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ipw_priv {int dummy; } ;
struct ipw_event {int dummy; } ;
typedef  int /*<<< orphan*/  base ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_EVENT_LOG ; 
 int ipw_read32 (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_read_indirect (struct ipw_priv*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ipw_capture_event_log(struct ipw_priv *priv,
				  u32 log_len, struct ipw_event *log)
{
	u32 base;

	if (log_len) {
		base = ipw_read32(priv, IPW_EVENT_LOG);
		ipw_read_indirect(priv, base + sizeof(base) + sizeof(u32),
				  (u8 *) log, sizeof(*log) * log_len);
	}
}
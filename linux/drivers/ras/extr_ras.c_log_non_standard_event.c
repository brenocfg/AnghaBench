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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 int /*<<< orphan*/  trace_non_standard_event (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const,int /*<<< orphan*/  const*,int /*<<< orphan*/  const) ; 

void log_non_standard_event(const guid_t *sec_type, const guid_t *fru_id,
			    const char *fru_text, const u8 sev, const u8 *err,
			    const u32 len)
{
	trace_non_standard_event(sec_type, fru_id, fru_text, sev, err, len);
}
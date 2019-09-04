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
typedef  int u32 ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int get_nvram_var (char const*,int /*<<< orphan*/ *,char const*,char*,int,int) ; 
 int kstrtou32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*,char const*,char*,int) ; 
 int /*<<< orphan*/  strim (char*) ; 

__attribute__((used)) static void nvram_read_leddc(const char *prefix, const char *name,
			     u8 *leddc_on_time, u8 *leddc_off_time,
			     bool fallback)
{
	char buf[100];
	int err;
	u32 val;

	err = get_nvram_var(prefix, NULL, name, buf, sizeof(buf), fallback);
	if (err < 0)
		return;
	err = kstrtou32(strim(buf), 0, &val);
	if (err) {
		pr_warn("can not parse nvram name %s%s with value %s got %i\n",
			prefix, name, buf, err);
		return;
	}

	if (val == 0xffff || val == 0xffffffff)
		return;

	*leddc_on_time = val & 0xff;
	*leddc_off_time = (val >> 16) & 0xff;
}
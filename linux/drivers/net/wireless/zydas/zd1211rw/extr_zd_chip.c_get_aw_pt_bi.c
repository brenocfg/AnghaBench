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
typedef  int /*<<< orphan*/  zd_addr_t ;
typedef  void* u32 ;
struct zd_chip {int dummy; } ;
struct aw_pt_bi {void* beacon_interval; void* pre_tbtt; void* atim_wnd_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
#define  CR_ATIM_WND_PERIOD 130 
#define  CR_BCN_INTERVAL 129 
#define  CR_PRE_TBTT 128 
 int /*<<< orphan*/  memset (struct aw_pt_bi*,int /*<<< orphan*/ ,int) ; 
 int zd_ioread32v_locked (struct zd_chip*,void**,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_aw_pt_bi(struct zd_chip *chip, struct aw_pt_bi *s)
{
	int r;
	static const zd_addr_t aw_pt_bi_addr[] =
		{ CR_ATIM_WND_PERIOD, CR_PRE_TBTT, CR_BCN_INTERVAL };
	u32 values[3];

	r = zd_ioread32v_locked(chip, values, (const zd_addr_t *)aw_pt_bi_addr,
		         ARRAY_SIZE(aw_pt_bi_addr));
	if (r) {
		memset(s, 0, sizeof(*s));
		return r;
	}

	s->atim_wnd_period = values[0];
	s->pre_tbtt = values[1];
	s->beacon_interval = values[2];
	return 0;
}
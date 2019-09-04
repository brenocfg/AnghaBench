#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct s3c_iotimings {TYPE_1__* bank; } ;
struct s3c_cpufreq_config {int dummy; } ;
struct s3c2412_iobank_timing {int dummy; } ;
struct TYPE_2__ {struct s3c2412_iobank_timing* io_2412; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int MAX_BANKS ; 
 int /*<<< orphan*/  S3C2412_EBI_BANKCFG ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bank_is_io (unsigned int,int /*<<< orphan*/ ) ; 
 struct s3c2412_iobank_timing* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2412_iotiming_getbank (struct s3c_cpufreq_config*,struct s3c2412_iobank_timing*,unsigned int) ; 
 int /*<<< orphan*/  s3c2412_print_timing (char*,struct s3c_iotimings*) ; 

int s3c2412_iotiming_get(struct s3c_cpufreq_config *cfg,
			 struct s3c_iotimings *timings)
{
	struct s3c2412_iobank_timing *bt;
	u32 bankcfg = __raw_readl(S3C2412_EBI_BANKCFG);
	unsigned int bank;

	/* look through all banks to see what is currently set. */

	for (bank = 0; bank < MAX_BANKS; bank++) {
		if (!bank_is_io(bank, bankcfg))
			continue;

		bt = kzalloc(sizeof(*bt), GFP_KERNEL);
		if (!bt)
			return -ENOMEM;

		timings->bank[bank].io_2412 = bt;
		s3c2412_iotiming_getbank(cfg, bt, bank);
	}

	s3c2412_print_timing("get", timings);
	return 0;
}
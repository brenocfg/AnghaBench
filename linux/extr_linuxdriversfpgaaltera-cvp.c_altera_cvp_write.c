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
typedef  int u32 ;
struct fpga_manager {struct altera_cvp_conf* priv; } ;
struct altera_cvp_conf {int /*<<< orphan*/  (* write_data ) (struct altera_cvp_conf*,int const) ;} ;

/* Variables and functions */
 int BIT (size_t) ; 
 size_t SZ_4K ; 
 int altera_cvp_chk_error (struct fpga_manager*,size_t) ; 
 scalar_t__ altera_cvp_chkcfg ; 
 int /*<<< orphan*/  stub1 (struct altera_cvp_conf*,int const) ; 
 int /*<<< orphan*/  stub2 (struct altera_cvp_conf*,int const) ; 

__attribute__((used)) static int altera_cvp_write(struct fpga_manager *mgr, const char *buf,
			    size_t count)
{
	struct altera_cvp_conf *conf = mgr->priv;
	const u32 *data;
	size_t done, remaining;
	int status = 0;
	u32 mask;

	/* STEP 9 - write 32-bit data from RBF file to CVP data register */
	data = (u32 *)buf;
	remaining = count;
	done = 0;

	while (remaining >= 4) {
		conf->write_data(conf, *data++);
		done += 4;
		remaining -= 4;

		/*
		 * STEP 10 (optional) and STEP 11
		 * - check error flag
		 * - loop until data transfer completed
		 * Config images can be huge (more than 40 MiB), so
		 * only check after a new 4k data block has been written.
		 * This reduces the number of checks and speeds up the
		 * configuration process.
		 */
		if (altera_cvp_chkcfg && !(done % SZ_4K)) {
			status = altera_cvp_chk_error(mgr, done);
			if (status < 0)
				return status;
		}
	}

	/* write up to 3 trailing bytes, if any */
	mask = BIT(remaining * 8) - 1;
	if (mask)
		conf->write_data(conf, *data & mask);

	if (altera_cvp_chkcfg)
		status = altera_cvp_chk_error(mgr, count);

	return status;
}
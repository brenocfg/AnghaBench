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
struct hideep_ts {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EBUSY ; 
 int HIDEEP_FLASH_PIO_SIG ; 
 int HIDEEP_NVM_PAGE_SIZE ; 
 int HIDEEP_PERASE ; 
 int HIDEEP_WRONLY ; 
 int /*<<< orphan*/  SET_FLASH_HWCONTROL () ; 
 int /*<<< orphan*/  SET_FLASH_PIO (int) ; 
 int /*<<< orphan*/  SET_PIO_SIG (int,int) ; 
 int be32_to_cpu (int /*<<< orphan*/  const) ; 
 int hideep_check_status (struct hideep_ts*) ; 
 int /*<<< orphan*/  hideep_pgm_w_mem (struct hideep_ts*,int,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int hideep_program_page(struct hideep_ts *ts, u32 addr,
			       const __be32 *ucode, size_t xfer_count)
{
	u32 val;
	int error;

	error = hideep_check_status(ts);
	if (error)
		return -EBUSY;

	addr &= ~(HIDEEP_NVM_PAGE_SIZE - 1);

	SET_FLASH_PIO(0);
	SET_FLASH_PIO(1);

	/* erase page */
	SET_PIO_SIG(HIDEEP_PERASE | addr, 0xFFFFFFFF);

	SET_FLASH_PIO(0);

	error = hideep_check_status(ts);
	if (error)
		return -EBUSY;

	/* write page */
	SET_FLASH_PIO(1);

	val = be32_to_cpu(ucode[0]);
	SET_PIO_SIG(HIDEEP_WRONLY | addr, val);

	hideep_pgm_w_mem(ts, HIDEEP_FLASH_PIO_SIG | HIDEEP_WRONLY,
			 ucode, xfer_count);

	val = be32_to_cpu(ucode[xfer_count - 1]);
	SET_PIO_SIG(124, val);

	SET_FLASH_PIO(0);

	usleep_range(1000, 1100);

	error = hideep_check_status(ts);
	if (error)
		return -EBUSY;

	SET_FLASH_HWCONTROL();

	return 0;
}
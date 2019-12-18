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
struct scaler_context {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SCALER_CFG ; 
 int SCALER_CFG_SOFT_RESET ; 
 int /*<<< orphan*/  SCALER_INT_EN ; 
 int SCALER_RESET_WAIT_RETRIES ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int scaler_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scaler_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int scaler_reset(struct scaler_context *scaler)
{
	int retry = SCALER_RESET_WAIT_RETRIES;

	scaler_write(SCALER_CFG_SOFT_RESET, SCALER_CFG);
	do {
		cpu_relax();
	} while (--retry > 1 &&
		 scaler_read(SCALER_CFG) & SCALER_CFG_SOFT_RESET);
	do {
		cpu_relax();
		scaler_write(1, SCALER_INT_EN);
	} while (--retry > 0 && scaler_read(SCALER_INT_EN) != 1);

	return retry ? 0 : -EIO;
}
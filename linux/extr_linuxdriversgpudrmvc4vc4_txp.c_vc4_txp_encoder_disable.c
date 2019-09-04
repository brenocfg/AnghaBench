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
struct vc4_txp {int dummy; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TXP_ABORT ; 
 int TXP_BUSY ; 
 int /*<<< orphan*/  TXP_DST_CTRL ; 
 int /*<<< orphan*/  TXP_POWERDOWN ; 
 int TXP_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXP_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct vc4_txp* encoder_to_vc4_txp (struct drm_encoder*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static void vc4_txp_encoder_disable(struct drm_encoder *encoder)
{
	struct vc4_txp *txp = encoder_to_vc4_txp(encoder);

	if (TXP_READ(TXP_DST_CTRL) & TXP_BUSY) {
		unsigned long timeout = jiffies + msecs_to_jiffies(1000);

		TXP_WRITE(TXP_DST_CTRL, TXP_ABORT);

		while (TXP_READ(TXP_DST_CTRL) & TXP_BUSY &&
		       time_before(jiffies, timeout))
			;

		WARN_ON(TXP_READ(TXP_DST_CTRL) & TXP_BUSY);
	}

	TXP_WRITE(TXP_DST_CTRL, TXP_POWERDOWN);
}
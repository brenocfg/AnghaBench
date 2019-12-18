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
struct cygnus_pinctrl {struct cygnus_mux_log* mux_log; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned int offset; unsigned int shift; scalar_t__ alt; } ;
struct cygnus_mux_log {int is_configured; TYPE_1__ mux; } ;

/* Variables and functions */
 int /*<<< orphan*/  CYGNUS_NUM_IOMUX ; 
 unsigned int CYGNUS_NUM_IOMUX_REGS ; 
 unsigned int CYGNUS_NUM_MUX_PER_REG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct cygnus_mux_log* devm_kcalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cygnus_mux_log_init(struct cygnus_pinctrl *pinctrl)
{
	struct cygnus_mux_log *log;
	unsigned int i, j;

	pinctrl->mux_log = devm_kcalloc(pinctrl->dev, CYGNUS_NUM_IOMUX,
					sizeof(struct cygnus_mux_log),
					GFP_KERNEL);
	if (!pinctrl->mux_log)
		return -ENOMEM;

	for (i = 0; i < CYGNUS_NUM_IOMUX_REGS; i++) {
		for (j = 0; j < CYGNUS_NUM_MUX_PER_REG; j++) {
			log = &pinctrl->mux_log[i * CYGNUS_NUM_MUX_PER_REG
				+ j];
			log->mux.offset = i * 4;
			log->mux.shift = j * 4;
			log->mux.alt = 0;
			log->is_configured = false;
		}
	}

	return 0;
}
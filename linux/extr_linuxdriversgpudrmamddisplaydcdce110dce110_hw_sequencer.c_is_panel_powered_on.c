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
typedef  int uint32_t ;
struct dce_hwseq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LVTMA_DIGON ; 
 int /*<<< orphan*/  LVTMA_DIGON_OVRD ; 
 int /*<<< orphan*/  LVTMA_PWRSEQ_CNTL ; 
 int /*<<< orphan*/  LVTMA_PWRSEQ_STATE ; 
 int /*<<< orphan*/  LVTMA_PWRSEQ_TARGET_STATE_R ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  REG_GET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool is_panel_powered_on(struct dce_hwseq *hws)
{
	uint32_t pwr_seq_state, dig_on, dig_on_ovrd;


	REG_GET(LVTMA_PWRSEQ_STATE, LVTMA_PWRSEQ_TARGET_STATE_R, &pwr_seq_state);

	REG_GET_2(LVTMA_PWRSEQ_CNTL, LVTMA_DIGON, &dig_on, LVTMA_DIGON_OVRD, &dig_on_ovrd);

	return (pwr_seq_state == 1) || (dig_on == 1 && dig_on_ovrd == 1);
}
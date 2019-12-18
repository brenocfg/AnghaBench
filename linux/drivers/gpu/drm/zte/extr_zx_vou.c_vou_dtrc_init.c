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
struct zx_vou_hw {scalar_t__ dtrc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DETILE_ARIDR_MODE_MASK ; 
 int /*<<< orphan*/  DETILE_ARID_IN_ARIDR ; 
 scalar_t__ DTRC_ARID ; 
 int DTRC_ARID0 (int) ; 
 int DTRC_ARID1 (int) ; 
 int DTRC_ARID2 (int) ; 
 int DTRC_ARID3 (int) ; 
 int /*<<< orphan*/  DTRC_DECOMPRESS_BYPASS ; 
 scalar_t__ DTRC_DETILE_CTRL ; 
 scalar_t__ DTRC_F0_CTRL ; 
 scalar_t__ DTRC_F1_CTRL ; 
 int /*<<< orphan*/  TILE2RASTESCAN_BYPASS_MODE ; 
 int /*<<< orphan*/  zx_writel (scalar_t__,int) ; 
 int /*<<< orphan*/  zx_writel_mask (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vou_dtrc_init(struct zx_vou_hw *vou)
{
	/* Clear bit for bypass by ID */
	zx_writel_mask(vou->dtrc + DTRC_DETILE_CTRL,
		       TILE2RASTESCAN_BYPASS_MODE, 0);

	/* Select ARIDR mode */
	zx_writel_mask(vou->dtrc + DTRC_DETILE_CTRL, DETILE_ARIDR_MODE_MASK,
		       DETILE_ARID_IN_ARIDR);

	/* Bypass decompression for both frames */
	zx_writel_mask(vou->dtrc + DTRC_F0_CTRL, DTRC_DECOMPRESS_BYPASS,
		       DTRC_DECOMPRESS_BYPASS);
	zx_writel_mask(vou->dtrc + DTRC_F1_CTRL, DTRC_DECOMPRESS_BYPASS,
		       DTRC_DECOMPRESS_BYPASS);

	/* Set up ARID register */
	zx_writel(vou->dtrc + DTRC_ARID, DTRC_ARID3(0xf) | DTRC_ARID2(0xe) |
		  DTRC_ARID1(0xf) | DTRC_ARID0(0xe));
}
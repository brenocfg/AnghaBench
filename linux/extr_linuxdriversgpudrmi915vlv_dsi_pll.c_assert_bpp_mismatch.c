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
typedef  enum mipi_dsi_pixel_format { ____Placeholder_mipi_dsi_pixel_format } mipi_dsi_pixel_format ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int,int) ; 
 int mipi_dsi_pixel_format_to_bpp (int) ; 

__attribute__((used)) static void assert_bpp_mismatch(enum mipi_dsi_pixel_format fmt, int pipe_bpp)
{
	int bpp = mipi_dsi_pixel_format_to_bpp(fmt);

	WARN(bpp != pipe_bpp,
	     "bpp match assertion failure (expected %d, current %d)\n",
	     bpp, pipe_bpp);
}
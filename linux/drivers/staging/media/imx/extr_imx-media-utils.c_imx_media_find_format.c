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
typedef  int /*<<< orphan*/  u32 ;
struct imx_media_pixfmt {int dummy; } ;
typedef  enum codespace_sel { ____Placeholder_codespace_sel } codespace_sel ;

/* Variables and functions */
 struct imx_media_pixfmt const* find_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

const struct imx_media_pixfmt *
imx_media_find_format(u32 fourcc, enum codespace_sel cs_sel, bool allow_bayer)
{
	return find_format(fourcc, 0, cs_sel, true, allow_bayer);
}
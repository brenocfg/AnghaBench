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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mtk_jpeg_dec_param {int dummy; } ;

/* Variables and functions */
 scalar_t__ mtk_jpeg_dec_fill_param (struct mtk_jpeg_dec_param*) ; 
 int /*<<< orphan*/  mtk_jpeg_do_parse (struct mtk_jpeg_dec_param*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool mtk_jpeg_parse(struct mtk_jpeg_dec_param *param, u8 *src_addr_va,
		    u32 src_size)
{
	if (!mtk_jpeg_do_parse(param, src_addr_va, src_size))
		return false;
	if (mtk_jpeg_dec_fill_param(param))
		return false;

	return true;
}
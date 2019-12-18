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
struct lima_ip {scalar_t__ iomem; } ;

/* Variables and functions */
 scalar_t__ LIMA_PP_FRAME ; 
 int LIMA_PP_FRAME_REG_NUM ; 
 scalar_t__ LIMA_PP_WB (int) ; 
 int LIMA_PP_WB_REG_NUM ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void lima_pp_write_frame(struct lima_ip *ip, u32 *frame, u32 *wb)
{
	int i, j, n = 0;

	for (i = 0; i < LIMA_PP_FRAME_REG_NUM; i++)
		writel(frame[i], ip->iomem + LIMA_PP_FRAME + i * 4);

	for (i = 0; i < 3; i++) {
		for (j = 0; j < LIMA_PP_WB_REG_NUM; j++)
			writel(wb[n++], ip->iomem + LIMA_PP_WB(i) + j * 4);
	}
}
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
struct scif_window {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  scif_off_to_dma_addr (struct scif_window*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline
dma_addr_t __scif_off_to_dma_addr(struct scif_window *window, s64 off)
{
	return scif_off_to_dma_addr(window, off, NULL, NULL);
}
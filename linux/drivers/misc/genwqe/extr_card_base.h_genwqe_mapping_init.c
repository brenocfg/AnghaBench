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
struct dma_mapping {int type; int write; } ;
typedef  enum dma_mapping_type { ____Placeholder_dma_mapping_type } dma_mapping_type ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct dma_mapping*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void genwqe_mapping_init(struct dma_mapping *m,
				       enum dma_mapping_type type)
{
	memset(m, 0, sizeof(*m));
	m->type = type;
	m->write = 1; /* Assume the maps we create are R/W */
}
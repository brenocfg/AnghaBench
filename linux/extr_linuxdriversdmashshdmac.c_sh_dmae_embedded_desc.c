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
struct shdma_desc {int dummy; } ;
struct sh_dmae_desc {struct shdma_desc shdma_desc; } ;

/* Variables and functions */

__attribute__((used)) static struct shdma_desc *sh_dmae_embedded_desc(void *buf, int i)
{
	return &((struct sh_dmae_desc *)buf)[i].shdma_desc;
}
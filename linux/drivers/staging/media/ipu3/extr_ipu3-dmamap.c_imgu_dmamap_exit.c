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
struct imgu_device {int /*<<< orphan*/  iova_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  iova_cache_put () ; 
 int /*<<< orphan*/  put_iova_domain (int /*<<< orphan*/ *) ; 

void imgu_dmamap_exit(struct imgu_device *imgu)
{
	put_iova_domain(&imgu->iova_domain);
	iova_cache_put();
}
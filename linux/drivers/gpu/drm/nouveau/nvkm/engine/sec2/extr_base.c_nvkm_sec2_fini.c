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
struct nvkm_sec2 {int /*<<< orphan*/  work; } ;
struct nvkm_engine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct nvkm_sec2* nvkm_sec2 (struct nvkm_engine*) ; 

__attribute__((used)) static int
nvkm_sec2_fini(struct nvkm_engine *engine, bool suspend)
{
	struct nvkm_sec2 *sec2 = nvkm_sec2(engine);
	flush_work(&sec2->work);
	return 0;
}
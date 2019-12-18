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
struct alg_spec {int /*<<< orphan*/  key; int /*<<< orphan*/  alg_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct alg_spec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void free_alg(struct alg_spec *a)
{
	kzfree(a->alg_string);
	kzfree(a->key);
	memset(a, 0, sizeof *a);
}
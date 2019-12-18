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
typedef  int u32 ;
struct qman_fq {int dummy; } ;

/* Variables and functions */
 struct qman_fq* idx_to_fq (int) ; 

__attribute__((used)) static struct qman_fq *fqid_to_fq(u32 fqid)
{
	return idx_to_fq(fqid * 2);
}
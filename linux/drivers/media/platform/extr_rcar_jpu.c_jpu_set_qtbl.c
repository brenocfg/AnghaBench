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
struct jpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  JCQTBL (int) ; 
 int /*<<< orphan*/  QTBL_SIZE ; 
 int /*<<< orphan*/  jpu_set_tbl (struct jpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * qtbl_chr ; 
 int /*<<< orphan*/ * qtbl_lum ; 

__attribute__((used)) static void jpu_set_qtbl(struct jpu *jpu, unsigned short quality)
{
	jpu_set_tbl(jpu, JCQTBL(0), qtbl_lum[quality], QTBL_SIZE);
	jpu_set_tbl(jpu, JCQTBL(1), qtbl_chr[quality], QTBL_SIZE);
}
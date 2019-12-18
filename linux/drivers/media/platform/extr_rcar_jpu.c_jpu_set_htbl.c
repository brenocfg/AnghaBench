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
 int /*<<< orphan*/  HACTBL_SIZE ; 
 int /*<<< orphan*/  HDCTBL_SIZE ; 
 int /*<<< orphan*/  JCHTBA (int) ; 
 int /*<<< orphan*/  JCHTBD (int) ; 
 int /*<<< orphan*/  hactbl_chr ; 
 int /*<<< orphan*/  hactbl_lum ; 
 int /*<<< orphan*/  hdctbl_chr ; 
 int /*<<< orphan*/  hdctbl_lum ; 
 int /*<<< orphan*/  jpu_set_tbl (struct jpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jpu_set_htbl(struct jpu *jpu)
{
	jpu_set_tbl(jpu, JCHTBD(0), hdctbl_lum, HDCTBL_SIZE);
	jpu_set_tbl(jpu, JCHTBA(0), hactbl_lum, HACTBL_SIZE);
	jpu_set_tbl(jpu, JCHTBD(1), hdctbl_chr, HDCTBL_SIZE);
	jpu_set_tbl(jpu, JCHTBA(1), hactbl_chr, HACTBL_SIZE);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long hclk_tns; } ;
struct s3c_cpufreq_config {TYPE_1__ freq; } ;
struct s3c2410_iobank_timing {unsigned long bankcon; int /*<<< orphan*/  tacc; void* tacs; void* tcos; void* tcoh; void* tcah; } ;

/* Variables and functions */
 unsigned long S3C2410_BANKCON_Tacc_SHIFT ; 
 unsigned long S3C2410_BANKCON_Tacs_SHIFT ; 
 unsigned long S3C2410_BANKCON_Tcah_SHIFT ; 
 unsigned long S3C2410_BANKCON_Tcoh_SHIFT ; 
 unsigned long S3C2410_BANKCON_Tcos_SHIFT ; 
 void* get_0124 (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  get_tacc (unsigned long,unsigned long) ; 

void s3c2410_iotiming_getbank(struct s3c_cpufreq_config *cfg,
			      struct s3c2410_iobank_timing *bt)
{
	unsigned long bankcon = bt->bankcon;
	unsigned long hclk = cfg->freq.hclk_tns;

	bt->tcah = get_0124(hclk, bankcon >> S3C2410_BANKCON_Tcah_SHIFT);
	bt->tcoh = get_0124(hclk, bankcon >> S3C2410_BANKCON_Tcoh_SHIFT);
	bt->tcos = get_0124(hclk, bankcon >> S3C2410_BANKCON_Tcos_SHIFT);
	bt->tacs = get_0124(hclk, bankcon >> S3C2410_BANKCON_Tacs_SHIFT);
	bt->tacc = get_tacc(hclk, bankcon >> S3C2410_BANKCON_Tacc_SHIFT);
}
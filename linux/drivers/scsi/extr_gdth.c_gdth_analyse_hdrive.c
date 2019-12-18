#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  size_t u16 ;
struct TYPE_6__ {int info; int info2; int cache_feat; TYPE_1__* hdr; int /*<<< orphan*/  hanum; } ;
typedef  TYPE_2__ gdth_ha_str ;
struct TYPE_5__ {int size; size_t devtype; void* rw_attribs; void* cluster_type; void* secs; void* heads; int /*<<< orphan*/  present; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHESERVICE ; 
 int GDT_64BIT ; 
 int /*<<< orphan*/  GDT_CLUST_INFO ; 
 int /*<<< orphan*/  GDT_DEVTYPE ; 
 int /*<<< orphan*/  GDT_INFO ; 
 int /*<<< orphan*/  GDT_RW_ATTRIBS ; 
 int /*<<< orphan*/  GDT_X_INFO ; 
 size_t MAX_HDRIVES ; 
 int SECS32 ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRACE2 (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gdth_eval_mapping (int,int*,int*,int*) ; 
 scalar_t__ gdth_internal_cmd (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shared_access ; 

__attribute__((used)) static int gdth_analyse_hdrive(gdth_ha_str *ha, u16 hdrive)
{
    u32 drv_cyls;
    int drv_hds, drv_secs;

    TRACE(("gdth_analyse_hdrive() hanum %d drive %d\n", ha->hanum, hdrive));
    if (hdrive >= MAX_HDRIVES)
        return 0;

    if (!gdth_internal_cmd(ha, CACHESERVICE, GDT_INFO, hdrive, 0, 0))
        return 0;
    ha->hdr[hdrive].present = TRUE;
    ha->hdr[hdrive].size = ha->info;
   
    /* evaluate mapping (sectors per head, heads per cylinder) */
    ha->hdr[hdrive].size &= ~SECS32;
    if (ha->info2 == 0) {
        gdth_eval_mapping(ha->hdr[hdrive].size,&drv_cyls,&drv_hds,&drv_secs);
    } else {
        drv_hds = ha->info2 & 0xff;
        drv_secs = (ha->info2 >> 8) & 0xff;
        drv_cyls = (u32)ha->hdr[hdrive].size / drv_hds / drv_secs;
    }
    ha->hdr[hdrive].heads = (u8)drv_hds;
    ha->hdr[hdrive].secs  = (u8)drv_secs;
    /* round size */
    ha->hdr[hdrive].size  = drv_cyls * drv_hds * drv_secs;
    
    if (ha->cache_feat & GDT_64BIT) {
        if (gdth_internal_cmd(ha, CACHESERVICE, GDT_X_INFO, hdrive, 0, 0)
            && ha->info2 != 0) {
            ha->hdr[hdrive].size = ((u64)ha->info2 << 32) | ha->info;
        }
    }
    TRACE2(("gdth_search_dr() cdr. %d size %d hds %d scs %d\n",
            hdrive,ha->hdr[hdrive].size,drv_hds,drv_secs));

    /* get informations about device */
    if (gdth_internal_cmd(ha, CACHESERVICE, GDT_DEVTYPE, hdrive, 0, 0)) {
        TRACE2(("gdth_search_dr() cache drive %d devtype %d\n",
                hdrive,ha->info));
        ha->hdr[hdrive].devtype = (u16)ha->info;
    }

    /* cluster info */
    if (gdth_internal_cmd(ha, CACHESERVICE, GDT_CLUST_INFO, hdrive, 0, 0)) {
        TRACE2(("gdth_search_dr() cache drive %d cluster info %d\n",
                hdrive,ha->info));
        if (!shared_access)
            ha->hdr[hdrive].cluster_type = (u8)ha->info;
    }

    /* R/W attributes */
    if (gdth_internal_cmd(ha, CACHESERVICE, GDT_RW_ATTRIBS, hdrive, 0, 0)) {
        TRACE2(("gdth_search_dr() cache drive %d r/w attrib. %d\n",
                hdrive,ha->info));
        ha->hdr[hdrive].rw_attribs = (u8)ha->info;
    }

    return 1;
}